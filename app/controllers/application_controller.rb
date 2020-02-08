# frozen_string_literal: true

# Base app controller with common filters
class ApplicationController < ActionController::Base
  def after_sign_in_path_for(_resource)
    root_path
  end

  def after_sign_out_path_for(_resource)
    root_path
  end

  private

  def require_admin
    return if current_user&.admin?

    redirect_to root_path, alert: 'You have no permission to view this page'
  end

  def error_message(obj)
    errors = obj.errors.full_messages.join '. '
    "Could not save due to errors: #{errors}"
  end

  def flash_errors(obj)
    flash[:alert] = error_message obj
  end

  def clear_error
    flash.delete(:alert)
  end
end
