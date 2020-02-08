# frozen_string_literal: true

# Shows users badges, total badges of all users, as well as info on the badges
class BadgesController < ApplicationController
  def index
    @badges = current_user.granted_badges if user_signed_in?

    @total_granted = GrantedBadge.count
    @total_users = GrantedBadge.all.group(:user_id).count.length
    logger.info("total is: #{@total_users}")
  end
end
